package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Multiplication;

import static org.junit.Assert.*;

public class MultiplicationTest {
	@Test
	public void execute() {
		Multiplication m = new Multiplication();
		ExecutionContext context = new ExecutionContext();
		Character a = 3;
		Character b = 2;
		context.getStack().push(a);
		context.getStack().push(b);
		m.execute(context);
		assertEquals(6, (int)context.getStack().peek());
	}
}