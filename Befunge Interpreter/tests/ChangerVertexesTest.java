package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.ChangerVertexes;

import static org.junit.Assert.*;

public class ChangerVertexesTest {
	@Test
	public void execute() {
		ChangerVertexes c = new ChangerVertexes();
		ExecutionContext context = new ExecutionContext();
		context.getStack().push('1');
		context.getStack().push('2');
		c.execute(context);
		assertEquals('1', (char) context.getStack().peek());
		context.getStack().pop();
		assertEquals('2', (char) context.getStack().peek());
	}
}