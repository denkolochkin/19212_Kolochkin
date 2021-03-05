package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.Interpreter;

import static org.junit.Assert.*;

public class InterpreterTest {
	@Test
	public void execute() {
		Interpreter i = new Interpreter();
		assertFalse(i.getEnd());
		i.read();
		i.execute();
		Character end = '@';
		assertEquals(i.getCommand(), end);
		assertEquals(i.getCommandName(), "End");
		assertTrue(i.getEnd());
	}
	@Test
	public void read() {
		Interpreter i = new Interpreter();
		i.read();
		Character a = '>';
		Character b = '.';
		assertEquals(i.getField().get(0).get(6), a);
		assertEquals(i.getField().get(2).get(5), b);
	}
}