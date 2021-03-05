package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;
import java.util.Scanner;

public class SymbolRequest implements Command {
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
