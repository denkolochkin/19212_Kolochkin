package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;
import org.apache.log4j.Logger;

public class End implements Command {
	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * This method set the End flag true.
	 */
	@Override
	public void execute(ExecutionContext context) {
		if (context.getCommandName().equals("End")) {
			log.trace("@ is executed");
			context.setEnd(true);
		}
	}
}
