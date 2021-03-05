package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Minus;

import static org.junit.Assert.*;

public class MinusTest {
	@Test
	public void execute() {
		Minus m = new Minus();
		ExecutionContext context = new ExecutionContext();
		Character a = 5;
		Character b = 3;
		context.getStack().push(a);
		context.getStack().push(b);
		m.execute(context);
		assertEquals(2, (int) context.getStack().peek());
	}
}