package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Mod implements Command {
	/**
	 * This method calculates
	 * mod of two closest numbers
	 * on the stack and pushes a result
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("% is executed");
		int a = context.getStack().pop() - '0';
		int b = context.getStack().pop() - '0';
		context.getStack().push((char)(b % a));
	}
}
