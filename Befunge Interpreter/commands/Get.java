package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;
import org.apache.log4j.Logger;

public class Get implements Command {
	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * This method takes two closest
	 * numbers on the stack like a position
	 * and pushes on the stack a symbol, which
	 * located on this position on the field.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("g is executed");
		int y = context.getStack().pop();
		int x = context.getStack().pop();
		context.getStack().push(context.getField().get(y).get(x));
	}
}
