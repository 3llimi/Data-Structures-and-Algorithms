//Ahmed Baha Eddine Alimi
import java.util.*;
 
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int N = input.nextInt();
        AVLTree<Integer> tree = new AVLTree<Integer>();
 
        for (int i = 0; i < N; i++) {
            int element = input.nextInt();
            tree.insert(element);
        }
 
        System.out.println(N);
        tree.printTree();
    }
}
 
// AVLTree class for a balanced binary search tree
class AVLTree<T extends Comparable<T>> {
    // Node class for each node in the AVL tree
    private class Node {
        T data;
        int index;
        Node left;
        Node right;
        int height;
 
        // Constructor to initialize a node with provided data and index
        Node(T value, int ind) {
            data = value;
            index = ind;
            left = null;
            right = null;
            height = 1;
        }
    }
 
    private Node root;
    private int currentIndex;
 
    // Method to get the height of a node
    private int getHeight(Node node) {
        if (node == null)
            return 0;
        return node.height;
    }
 
    // Method to calculate the balance factor of a node
    private int getBalanceFactor(Node node) {
        if (node == null)
            return 0;
        return getHeight(node.left) - getHeight(node.right);
    }
 
    // Method to perform a right rotation on a node
    private Node rightRotation(Node node) {
        Node newRoot = node.left;
        node.left = newRoot.right;
        newRoot.right = node;
 
        node.height = 1 + Math.max(getHeight(node.left), getHeight(node.right));
        newRoot.height = 1 + Math.max(getHeight(newRoot.left), getHeight(newRoot.right));
 
        return newRoot;
    }
 
    // Method to perform a left rotation on a node
    private Node leftRotation(Node node) {
        Node newRoot = node.right;
        node.right = newRoot.left;
        newRoot.left = node;
 
        node.height = 1 + Math.max(getHeight(node.left), getHeight(node.right));
        newRoot.height = 1 + Math.max(getHeight(newRoot.left), getHeight(newRoot.right));
 
        return newRoot;
    }
 
    // Method to insert a node with a given value into the AVL tree
    private Node insertNode(Node node, T value) {
        if (node == null)
            return new Node(value, ++currentIndex);
 
        if (value.compareTo(node.data) < 0)
            node.left = insertNode(node.left, value);
        else if (value.compareTo(node.data) > 0)
            node.right = insertNode(node.right, value);
        else
            return node;
 
        node.height = 1 + Math.max(getHeight(node.left), getHeight(node.right));
 
        int balanceFactor = getBalanceFactor(node);
 
        if (balanceFactor > 1) {
            if (value.compareTo(node.left.data) < 0)
                return rightRotation(node);
            else {
                node.left = leftRotation(node.left);
                return rightRotation(node);
            }
        }
 
        if (balanceFactor < -1) {
            if (value.compareTo(node.right.data) > 0)
                return leftRotation(node);
            else {
                node.right = rightRotation(node.right);
                return leftRotation(node);
            }
        }
 
        return node;
    }
 
    // Method for inorder traversal of the AVL tree
    private void inorderTraversal(Node node) {
        if (node == null)
            return;
 
        inorderTraversal(node.left);
        System.out.println(node.data + " " + (node.left != null ? node.left.data : -1) + " "
                + (node.right != null ? node.right.data : -1));
        inorderTraversal(node.right);
    }
 
    // Constructor to initialize an empty AVL tree
    public AVLTree() {
        root = null;
        currentIndex = 0;
    }
 
    // Method to insert a new value into the AVL tree
    public void insert(T value) {
        root = insertNode(root, value);
    }
 
    public void printTree() {
        inorderTraversal(root);
        System.out.println(root.data);
    }
}