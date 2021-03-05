package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Plus implements Command {
	/**
	 * This method adds up two
	 * closest numbers on the stack
	 * and pushes a result.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("+ is executed");
		int a = context.getStack().pop();
		int b = context.getStack().pop();
		int c = b + a;
		context.getStack().push((char)c);
	}
}
