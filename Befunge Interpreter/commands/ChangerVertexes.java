package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class ChangerVertexes implements Command {
	/**
	 * This method swaps two closest
	 * objects on the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("\\ is executed");
		Character a = context.getStack().pop();
		Character b = context.getStack().pop();
		context.getStack().push(a);
		context.getStack().push(b);
	}
}
