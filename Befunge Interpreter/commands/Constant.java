package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;
import org.apache.log4j.Logger;

public class Constant implements Command{
	Logger log = Logger.getLogger(Interpreter.class.getName());
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
