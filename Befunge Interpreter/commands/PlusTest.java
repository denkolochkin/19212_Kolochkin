package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class PlusTest {

	@Test
	public void execute() {
		Plus p = new Plus();
		Stack<Character> stack = new Stack<>();
		stack.push('4');
		stack.push('3');
		p.execute(stack, null, null, null);
		assertEquals('7',  stack.peek() - '0');
	}
}