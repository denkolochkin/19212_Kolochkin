package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public class Direction implements Command {
	/**
	 * This method changes the direction
	 * in depends on command. Conditional
	 * change of direction by commands '_'
	 * and '|'.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("Direction is executed");
		if (context.getCommand().equals('_')) {
			if(context.getStack().pop() == 0) {
				context.setDirection('>');
				return;
			}
			else {
				context.setDirection('<');
				return;
			}
		}
		if (context.getCommand().equals('|')) {
			if (context.getStack().pop() == 0) {
				context.setDirection('v');
				return;
			}
			else {
				context.setDirection('^');
				return;
			}
		}
		if (context.getCommand().equals('?')) {
			char[] directions = {'^', '<', '>', 'v'};
			int index = (int) (Math.random() * 3);
			context.setDirection(directions[index]);
			return;
		}
		if (context.getCommand().equals('#')) {
			context.move();
			return;
		}
		context.setDirection(context.getCommand());
	}
}
