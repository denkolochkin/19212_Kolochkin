package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import java.io.IOException;

public class NumberRequest implements Command {
	/**
	 * This method reads a number
	 * and pushes him on the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("& is executed");
		try {
			context.getStack().push((char) context.getInputStream().read());
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
