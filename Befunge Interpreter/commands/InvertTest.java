package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class InvertTest {

	@Test
	public void execute() {
		Invert i = new Invert();
		Stack<Character> stack = new Stack<>();
		stack.push('0');
		i.execute(stack, null, null, null);
		assertEquals('1', (char) stack.peek());
		i.execute(stack, null, null, null);
		assertEquals('0', (char) stack.peek());
	}
}