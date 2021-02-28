package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class ComparisonTest {

	@Test
	public void execute() {
		Comparison c = new Comparison();
		Stack<Character> stack = new Stack<>();
		stack.push('4');
		stack.push('8');
		c.execute(stack, null, null, null);
		assertEquals(0, (int) stack.peek());
		stack.clear();
		stack.push('8');
		stack.push('4');
		c.execute(stack, null, null, null);
		assertEquals(1, (int) stack.peek());
	}
}