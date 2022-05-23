import java.io.IOException;

public class Main {
	public static void main(String[] args) {
		String locationName = args[0];
		String locale = args[1];
		String radius = args[2];
		if (Integer.parseInt(radius) < 0) {
			System.out.println("Wrong radius");
			return;
		}
		Worker worker = new Worker();
		try {
			worker.run(locationName, locale, radius);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
