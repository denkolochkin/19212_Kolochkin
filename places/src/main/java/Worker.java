import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import org.asynchttpclient.AsyncHttpClient;
import org.asynchttpclient.Response;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.atomic.AtomicInteger;

import static org.asynchttpclient.Dsl.*;

public class Worker {

	AsyncHttpClient asyncHttpClient = asyncHttpClient();

	private CompletableFuture<Response> getRequest(String url) throws IOException {
		return asyncHttpClient.executeRequest(get(url).build()).toCompletableFuture();
	}

	public <T> CompletableFuture<List<T>> sequence(final List<CompletableFuture<T>> futures) {
		CompletableFuture<List<T>> completableFuture = new CompletableFuture<>();
		final int total = futures.size();
		final AtomicInteger counter = new AtomicInteger();
		final List<T> results = new ArrayList<>(futures.size());
		futures.forEach(f -> f.whenComplete((ok, error) -> {
			if (error == null) {
				synchronized (results) {
					results.add(ok);
				}
			}
			int totalDone = counter.incrementAndGet();
			if (totalDone == total) {
				completableFuture.complete(results);
			}
		}));
		return completableFuture;
	}

	private CompletableFuture<String> parseWeather(CompletableFuture<Response> jsonWeather) {
		return jsonWeather.thenApply(response -> {
			JsonObject json = (JsonObject) JsonParser.parseString(response.getResponseBody());
			return "Weather description: " +  json.getAsJsonObject().get("weather").getAsJsonArray().get(0).
					getAsJsonObject().get("description").toString() + "\nTemperature: " +
					json.getAsJsonObject().get("main").getAsJsonObject().get("temp").toString() + " K\nWind speed: "
					+ json.getAsJsonObject().get("wind").getAsJsonObject().get("speed").toString() + " m/s";
		});
	}

	private CompletableFuture<List<String>> getWeather(Place[] places) {
		List<CompletableFuture<String>> weathers = new ArrayList<>();
		for (Place place : places) {
			String url = "https://api.openweathermap.org/data/2.5/weather" + "?lat=" + place.latitude + 
					"&lon=" + place.longitude + "&appid=0b7f9f5dd535f4f4c32e7eea9e916e55";
			try {
				weathers.add(parseWeather(getRequest(url)));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return sequence(weathers);
	}

	private CompletableFuture<String[]> parseInterestingPlaces(CompletableFuture<Response> jsonPlaces) {
		return jsonPlaces.thenApply(response -> {
			JsonObject json = (JsonObject) JsonParser.parseString(response.getResponseBody());
			int placesSize = json.get("features").getAsJsonArray().size();
			String[] interestingPlaces = new String[placesSize];
			for (int j = 0; j < placesSize; j++) {
				JsonObject currentObject = json.getAsJsonArray("features").getAsJsonArray().get(j).
						getAsJsonObject().get("properties").getAsJsonObject();
				interestingPlaces[j] = "Name: " + currentObject.get("name") + " Distance: "
						+ currentObject.get("dist") + " Kinds: " + currentObject.get("kinds");
			}
			return interestingPlaces;
		});
	}

	private CompletableFuture<List<String[]>> getInterestingPlaces(Place[] places, int radius) {
		ArrayList<CompletableFuture<String[]>> interestingPlaces = new ArrayList<>();
		for (Place place : places) {
			String url = "https://api.opentripmap.com/0.1/ru/places/radius?radius=" + radius + "&lon=" + 
					place.longitude + "&lat=" + place.latitude + "&apikey=" + 
					"5ae2e3f221c38a28845f05b668f33917837a7d1ed991a581d46cec80";
			try {
				interestingPlaces.add(parseInterestingPlaces(getRequest(url)));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return sequence(interestingPlaces);
	}

	private CompletableFuture<Place[]> parseGeocode(CompletableFuture<Response> jsonGeocode) {
		return jsonGeocode.thenApply(response -> {
			JsonObject json = (JsonObject)JsonParser.parseString(response.getResponseBody());
			int placesSize = json.get("hits").getAsJsonArray().size();
			Place[] places = new Place[placesSize];
			for (int i = 0; i < placesSize; i++) {
				places[i] = new Place();
				JsonObject currentPlace = (JsonObject)json.get("hits").getAsJsonArray().get(i);
				places[i].latitude = currentPlace.get("point").getAsJsonObject().get("lat").toString();
				places[i].longitude = currentPlace.get("point").getAsJsonObject().get("lng").toString();
				places[i].country = currentPlace.get("country").toString();
				places[i].name = currentPlace.get("name").toString();
			}
			return places;
		});
	}

	private CompletableFuture<Place[]> getGeocode(String locationName, String locale)  {
		String url = "https://graphhopper.com/api/1/geocode?q=" + locationName + "&locale=" + locale +
				"&debug=true&key=ba111415-0e93-4cd2-a294-17dbf0b6f4a0";
		CompletableFuture<Place[]> places = new CompletableFuture<>();
		try {
			places = parseGeocode(getRequest(url));
		} catch (IOException e) {
			e.printStackTrace();
		}
		return places;
	}

	public void run(String locationName, String locale, String radius) throws IOException {
		CompletableFuture<Place[]> coordsFuture = getGeocode(locationName, locale);
		coordsFuture.thenApply(coords -> {
			CompletableFuture<List<String[]>> placesFuture = getInterestingPlaces(coords, Integer.parseInt(radius));
			CompletableFuture<List<String>> weatherFuture = getWeather(coords);
			return placesFuture.<List<String>, Place[]>thenCombine(weatherFuture, (placesResult, weatherResult) -> {
				Printer printer = new Printer();
				printer.print(coords, placesResult, weatherResult);
				try {
					asyncHttpClient.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
				return null;
			});
		});
	}

}
