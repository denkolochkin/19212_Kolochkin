package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;
import org.apache.log4j.Logger;

public class SymbolMode implements Command {
	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * This method pushes on the stack
	 * elements between "" from the field.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("\" is executed");
		context.move();
		while (!context.getField().get(context.getY()).get(context.getX()).equals('"')) {
			context.getStack().push(context.getField().get(context.getY()).get(context.getX()));
			context.move();
		}
	}
}
