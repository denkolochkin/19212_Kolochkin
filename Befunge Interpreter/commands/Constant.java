package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Constant implements Command{
	/**
	 * This method push the constant
	 * on the stack
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("Constant is executed");
		int a = Character.getNumericValue(context.getCommand());
		context.getStack().push((char) a);
	}
}
