package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.NumberPrint;
import static org.junit.Assert.*;

public class NumberPrintTest {
	@Test
	public void execute() {
		ExecutionContext c = new ExecutionContext();
		NumberPrint p = new NumberPrint();
		Character a = 4;
		c.getStack().push(a);
		p.execute(c);
		assertTrue(c.getOutputStream().getBuffer().contains((char) 4));
	}
}