package ru.nsu.kolochkin.Befunge.tests;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.ExecutionContext;
import ru.nsu.kolochkin.Befunge.commands.Direction;

import static org.junit.Assert.*;

public class DirectionTest {
	@Test
	public void execute() {
		ExecutionContext c = new ExecutionContext();
		Direction d = new Direction();
		Character right = '>';
		Character bottom = 'v';
		Character top = '^';
		Character left = '<';
		Character a = 0;
		Character b = 1;
		c.setCommand(right);
		d.execute(c);
		assertEquals(c.getDirection(), right);
		c.setCommand('|');
		c.getStack().push(a);
		d.execute(c);
		assertTrue(c.getDirection() == bottom);
		c.setCommand('|');
		c.getStack().push(b);
		d.execute(c);
		assertTrue(c.getDirection() == top);
		c.setCommand('_');
		c.getStack().push(a);
		d.execute(c);
		assertTrue(c.getDirection() == right);
		c.setCommand('_');
		c.getStack().push(b);
		d.execute(c);
		assertTrue(c.getDirection() == left);
		c.setCommand('?');
		d.execute(c);
		assertTrue(c.getDirection() == right || c.getDirection() == left
				|| c.getDirection() == top || c.getDirection() == bottom);
	}
}