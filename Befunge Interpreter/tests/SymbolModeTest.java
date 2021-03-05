package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.SymbolMode;

import java.util.ArrayList;
import static org.junit.Assert.*;

public class SymbolModeTest {
	@Test
	public void execute() {
		ExecutionContext i = new ExecutionContext();
		SymbolMode s = new SymbolMode();
		ArrayList<Character> l = new ArrayList<>();
		l.add('"');
		for (int j = 0; j < 3; j++) {
			l.add((char) j);
		}
		l.add('"');
		i.getField().add(l);
		s.execute(i);
		assertEquals((int) i.getStack().pop(), 2);
		assertEquals((int) i.getStack().pop(), 1);
		assertEquals((int) i.getStack().pop(), 0);
	}
}