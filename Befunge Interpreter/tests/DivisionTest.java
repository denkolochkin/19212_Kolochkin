package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Division;

import static org.junit.Assert.*;

public class DivisionTest {
	@Test
	public void execute() {
		Division d = new Division();
		ExecutionContext context = new ExecutionContext();
		context.getStack().push('4');
		context.getStack().push('6');
		d.execute(context);
		assertEquals(0, (int) context.getStack().peek());
		context.getStack().push('4');
		context.getStack().push('2');
		d.execute(context);
		assertEquals(2, (int) context.getStack().peek());
	}
}