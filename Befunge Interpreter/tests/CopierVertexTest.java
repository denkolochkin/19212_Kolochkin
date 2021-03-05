package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.CopierVertex;

import static org.junit.Assert.*;

public class CopierVertexTest {
	@Test
	public void execute() {
		CopierVertex c = new CopierVertex();
		ExecutionContext context = new ExecutionContext();
		context.getStack().push('>');
		c.execute(context);
		assertEquals(context.getStack().pop(), context.getStack().pop());
	}
}