package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class ConstantTest {

	@Test
	public void execute() {
		Stack<Character> stack = new Stack<>();
		Character command = '7';
		Constant c = new Constant();
		c.execute(stack, command, null, null);
		assertEquals(7, (int) stack.peek());
		command = '3';
		c.execute(stack, command, null, null);
		assertNotEquals(7, (int) stack.peek());
	}
}