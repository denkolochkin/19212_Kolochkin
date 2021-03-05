package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;
import org.apache.log4j.Logger;

public class Deleter implements Command {
	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * This method deletes
	 * top of the stack.
	 */
	@Override
	public void execute(ExecutionContext  context) {
		log.trace("$ is executed");
		context.getStack().pop();
	}
}
