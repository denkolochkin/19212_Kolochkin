package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Comparison implements Command {
	/**
	 * This method compares two closest
	 * objects on the stack. In depends
	 * on which one is bigger pushes
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("' is executed");
		int a = context.getStack().pop();
		int b = context.getStack().pop();
		if (a < b) {
			context.getStack().push((char) b);
			context.getStack().push((char) a);
			context.getStack().push((char) 1);
		}
		else {
			context.getStack().push((char) b);
			context.getStack().push((char) a);
			context.getStack().push((char) 0);
		}
	}
}
