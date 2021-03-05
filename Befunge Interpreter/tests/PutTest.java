package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.Interpreter;
import ru.nsu.kolochkin.Befunge.commands.Put;

import static org.junit.Assert.*;

public class PutTest {
	@Test
	public void execute() {
		Put p = new Put();
		Interpreter i = new Interpreter();
		i.read();
		Character y = 1;
		Character x = 3;
		Character a = 8;
		i.getStack().push(a);
		i.getStack().push(x);
		i.getStack().push(y);
		p.execute(i);
		assertEquals(i.getField().get(y).get(x), a);
	}
}