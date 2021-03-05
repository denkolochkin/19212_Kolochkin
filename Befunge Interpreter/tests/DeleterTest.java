package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Deleter;

import static org.junit.Assert.*;

public class DeleterTest {
	@Test
	public void execute() {
		Deleter d = new Deleter();
		ExecutionContext context = new ExecutionContext();
		context.getStack().push('1');
		context.getStack().push('3');
		d.execute(context);
		assertNotEquals('3', (char) context.getStack().peek());
		assertEquals('1', (char) context.getStack().peek());
	}
}