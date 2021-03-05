package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Invert;

import static org.junit.Assert.*;

public class InvertTest {
	@Test
	public void execute() {
		Invert i = new Invert();
		ExecutionContext context = new ExecutionContext();
		context.getStack().push('0');
		i.execute(context);
		assertEquals('1', (char) context.getStack().peek());
		i.execute(context);
		assertEquals('0', (char) context.getStack().peek());
	}
}