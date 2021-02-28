package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class MinusTest {

	@Test
	public void execute() {
		Minus m = new Minus();
		Stack<Character> stack = new Stack<>();
		stack.push('5');
		stack.push('3');
		m.execute(stack, null, null, null);
		assertEquals(2, (int) stack.peek());
	}
}