package ru.nsu.kolochkin.Befunge.commands;

import org.apache.log4j.Logger;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.Interpreter;

public interface Command {

	Logger log = Logger.getLogger(Interpreter.class.getName());
	/**
	 * Virtual method, that overrides
	 * if every command.
	 */
	void execute(ExecutionContext context);
}
