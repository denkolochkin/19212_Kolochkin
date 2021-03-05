package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Constant;

import static org.junit.Assert.*;

public class ConstantTest {
	@Test
	public void execute() {
		Constant c = new Constant();
		ExecutionContext context = new ExecutionContext();
		context.setCommand('7');
		c.execute(context);
		assertEquals(7, (int) context.getStack().peek());
		context.setCommand('3');
		c.execute(context);
		assertNotEquals(7, (int) context.getStack().peek());
	}
}