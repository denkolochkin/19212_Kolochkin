package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;
import java.util.Scanner;
import org.apache.log4j.Logger;

public class SymbolRequest implements Command {
	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * This method reads a symbol
	 * and pushes him on the stack.
	 */
	@Override
	public void execute(ExecutionContext context) {
		log.trace("~ is executed");
		Scanner scanner = new Scanner(System.in);
		context.getStack().push((scanner.next()).charAt(0));
	}
}
