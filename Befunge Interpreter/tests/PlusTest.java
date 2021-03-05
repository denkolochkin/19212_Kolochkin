package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Plus;

import static org.junit.Assert.*;

public class PlusTest {
	@Test
	public void execute() {
		Plus p = new Plus();
		ExecutionContext context = new ExecutionContext();
		Character a = 4;
		Character b = 3;
		context.getStack().push(a);
		context.getStack().push(b);
		p.execute(context);
		assertEquals(7, (int)context.getStack().peek());
	}
}