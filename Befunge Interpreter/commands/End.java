package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class End implements Command {
	/**
	 * This method set the End flag true.
	 */
	@Override
	public void execute(ExecutionContext context) {
		if (context.getCommandName().equals("End")) {
			log.trace("@ is executed");
			context.setEnd(true);
		}
	}
}
