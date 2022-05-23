import java.util.List;

public class Printer {

	public void print(Place[] coords, List<String[]> places, List<String> weathers) {
		for (int i = 0; i < coords.length; i++) {
			System.out.println("Longitude: " + coords[i].longitude + "\nLatitude: " + coords[i].latitude +
					"\nCountry: " + coords[i].country + "\nName: " + coords[i].name);
			if (places.get(i).length == 0) {
				System.out.println("No interesting places close");
			} else {
				System.out.println("-----Interesting places-----");
				for (int j = 0; j < places.get(i).length; j++) {
					System.out.println(places.get(i)[j]);
				}
			}
			System.out.println("-----Weather-----");
			System.out.println(weathers.get(i));
			System.out.println("==================================");
		}
	}

}
