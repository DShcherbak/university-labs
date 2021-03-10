package org.example;

import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class LinkedList {
    public static class ListNode{
        int value;
        ListNode next;

        public ListNode(int v){
            value = v;
            next = null;
        }
    }

    ListNode head;
    ReadWriteLock lock;
    int id;

    public LinkedList(int id){
        head = null;
        lock = new ReentrantReadWriteLock();
        this.id = id;
    }

    public boolean Find(int value) {
        lock.readLock().lock();
        if(head == null){
            return false;
        }
        ListNode cur = head;
        while(cur.next != null && cur.next.value < value){
            cur = cur.next;
        }
        boolean returnValue = cur.next == null || cur.next.value > value;
        lock.readLock().unlock();
        return returnValue;
    }

    public void Insert(int value){
        ListNode node = new ListNode(value);
        if(Find(value))
            return;
        lock.writeLock().lock();
        if(head == null){
            head = node;
            lock.writeLock().unlock();
            return;
        }
        ListNode cur = head;
        while(cur.next != null && cur.next.value < value){
            cur = cur.next;
        }
        node.next = cur.next;
        cur.next = node;
        lock.writeLock().unlock();
    }

    public void Delete(int value){
        if(!Find(value))
            return;
        lock.writeLock().lock();
        if(head == null){
            lock.writeLock().unlock();
            return;
        }
        ListNode cur = head;
        while(cur.next != null && cur.next.value < value){
            cur = cur.next;
        }
        if(cur.next != null){
            cur.next = cur.next.next;
        }
        lock.writeLock().unlock();
    }
}
