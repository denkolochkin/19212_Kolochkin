package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class DivisionTest {

	@Test
	public void execute() {
		Division d = new Division();
		Stack<Character> stack = new Stack<>();
		stack.push('4');
		stack.push('6');
		d.execute(stack, null, null, null);
		assertEquals(0, (int) stack.peek());
		stack.push('4');
		stack.push('2');
		d.execute(stack, null, null, null);
		assertEquals(2, (int) stack.peek());
	}
}