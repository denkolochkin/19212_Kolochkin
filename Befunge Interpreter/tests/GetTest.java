package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.Interpreter;
import ru.nsu.kolochkin.Befunge.commands.Get;

import static org.junit.Assert.*;

public class GetTest {
	@Test
	public void execute() {
		Get g = new Get();
		Interpreter i = new Interpreter();
		i.read();
		Character y = 1;
		Character x = 5;
		i.getStack().push(x);
		i.getStack().push(y);
		g.execute(i);
		assertEquals((char) i.getStack().peek(), '0');
	}
}