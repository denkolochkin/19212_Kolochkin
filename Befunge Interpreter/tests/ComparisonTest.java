package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Comparison;

import static org.junit.Assert.*;

public class ComparisonTest {
	@Test
	public void execute() {
		Comparison c = new Comparison();
		ExecutionContext context = new ExecutionContext();
		context.getStack().push('4');
		context.getStack().push('8');
		c.execute(context);
		assertEquals(0, (int) context.getStack().peek());
		context.getStack().clear();
		context.getStack().push('8');
		context.getStack().push('4');
		c.execute(context);
		assertEquals(1, (int) context.getStack().peek());
	}
}