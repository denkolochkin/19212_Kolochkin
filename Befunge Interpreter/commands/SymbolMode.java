package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class SymbolMode implements Command {
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
