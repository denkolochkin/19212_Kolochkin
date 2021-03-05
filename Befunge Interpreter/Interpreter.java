package ru.nsu.kolochkin.Befunge;

import ru.nsu.kolochkin.Befunge.commands.Command;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Properties;
import org.apache.log4j.Logger;

/**
 * @version 1.2
 * The Befunge interpreter reads and
 * executes commands on Befunge from .txt file.
 */

public class Interpreter extends ExecutionContext {

	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * @see CommandFactory
	 */
	private final CommandFactory factory = new CommandFactory();
	/**
	 * This method executes every command
	 * from file until he meets '@'.
	 */
	public void execute() {
		Properties properties = new Properties();
		try {
			log.info("Loading properties...");
			properties.load(new FileReader("/Users/deniskolockin/" +
										   "IdeaProjects/Befunge/src/ru/nsu/" +
										   "kolochkin/Befunge/config.properties"));
		} catch (IOException e) {
			log.error("Loading properties error.");
			e.printStackTrace();
		}
		log.info("Properties was loaded");
		log.info("Start of execution.");
		while(!end) {
			command = field.get(y).get(x);
			commandName = properties.getProperty(command.toString());
			Command c = factory.createCommand(commandName);
			assert c != null;
			c.execute(this);
			if (!end) {
				move();
			}
		}
		//for logger
		System.out.println();
		log.info("End of execution.");
	}
	/**
	 * This method reads .txt file and
	 * saves in ArrayList with sizes
	 * 25*80.
	 */
	public void read() {
		log.info("Reading...");
		try (FileReader fr = new FileReader("/Users/deniskolockin/" +
										   "IdeaProjects/Befunge/" +
										   "BefungePrograms/fib.txt")) {
			Scanner scanner = new Scanner(fr);
			int countY = 0;
			while (scanner.hasNextLine()) {
				String tmp = scanner.nextLine();
				ArrayList<Character> l = new ArrayList<>();
				for (int i = 0; i < tmp.length(); i++) {
					l.add(tmp.charAt(i));
				}
				for (int i = tmp.length(); i < 80; i++) {
					l.add(' ');
				}
				field.add(l);
				countY++;
			}
			ArrayList<Character> l = new ArrayList<>();
			for (int i = 0; i < 80; i++) {
				l.add(' ');
			}
			for (int i = countY; i < 25; i++) {
				field.add(l);
			}
		} catch (IOException e) {
			log.error("File reading error.");
			e.printStackTrace();
		}
		log.info("End reading.");
	}
}
