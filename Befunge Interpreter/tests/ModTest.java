package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Mod;

import static org.junit.Assert.*;

public class ModTest {
	@Test
	public void execute() {
		Mod m = new Mod();
		ExecutionContext context = new ExecutionContext();
		context.getStack().push('7');
		context.getStack().push('5');
		m.execute(context);
		assertEquals(2, (int) context.getStack().peek());
	}
}