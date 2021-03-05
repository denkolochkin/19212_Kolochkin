package ru.nsu.kolochkin.Befunge;

import ru.nsu.kolochkin.Befunge.commands.Command;
import java.util.HashMap;
import java.util.logging.Logger;

/**
 * This class creates objects of commands
 * by the name of the command.
 */
public class CommandFactory {
	static Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * Used for caching of commands objects.
	 */
	private static HashMap<String, Command> classMap = new HashMap<>();

	/**
	 * This method returns finished object
	 * of the command. If we try to load
	 * class not the first time, will return
	 * finished object from classMap.
	 */
	public static Command createCommand(String commandName) {
		Class<?> cl = null;
		if (!classMap.containsKey(commandName)) {
			try {
				cl = Class.forName("ru.nsu.kolochkin.Befunge.commands." + commandName);
				log.info("Trying to create command " + commandName);
			} catch (ClassNotFoundException e) {
				log.throwing("CommandFactory", "createCommand", e);
				return null;
			}
			Object o;
			try {
				o = cl.newInstance();
			} catch (InstantiationException | IllegalAccessException e) {
				log.throwing("CommandFactory", "createCommand", e);
				return null;
			}
			Command c = (Command) o;
			classMap.put(commandName, c);
			return c;
		}
		else {
			return classMap.get(commandName);
		}
	}
}
