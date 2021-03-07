package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.SymbolPrint;
import static org.junit.Assert.*;

public class SymbolPrintTest {
	@Test
	public void execute() {
		ExecutionContext c = new ExecutionContext();
		SymbolPrint s = new SymbolPrint();
		System.setOut(c.getOutputStream());
		c.getStack().push('z');
		s.execute(c);
		assertEquals(c.getOutputStream().toString(), 'z');
	}
}