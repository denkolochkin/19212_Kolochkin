package ru.nsu.kolochkin.Befunge.commands;

import ru.nsu.kolochkin.Befunge.ExecutionContext;

public interface Command {
	/**
	 * Virtual method, that overrides
	 * if every command.
	 */
	void execute(ExecutionContext context);
}
