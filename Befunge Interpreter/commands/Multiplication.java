package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;
import org.apache.log4j.Logger;

public class Multiplication implements Command {
	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * This method multiplicities two
	 * closest numbers on the stack
	 * and pushes a result.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("* is executed");
		int a = context.getStack().pop();
		int b = context.getStack().pop();
		context.getStack().push((char)(b * a));
	}
}
