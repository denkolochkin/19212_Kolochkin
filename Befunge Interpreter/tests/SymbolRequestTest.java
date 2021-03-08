package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import static org.junit.Assert.*;

public class SymbolRequestTest {
	@Test
	public void execute() {
		ExecutionContext c = new ExecutionContext();
		Character a = 'r';
		c.getInputStream().getBuffer().add(a);
		assertTrue(c.getInputStream().getBuffer().contains(a));
		assertTrue(c.getOutputStream().getBuffer().contains(a));
	}
}