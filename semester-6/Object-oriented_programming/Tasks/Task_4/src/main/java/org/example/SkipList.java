package org.example;

import java.util.ArrayList;

public class SkipList {

    ArrayList<LinkedList> lists;

    public SkipList(int height){
        lists = new ArrayList<>(height);
        for(int i = 0; i < height; i++){
            lists.set(i, new LinkedList(i));
        }
    }

    public boolean Find(int value) {
        lock.readLock().lock();
        if(head == null){
            return false;
        }
        LinkedList.ListNode cur = head;
        while(cur.next != null && cur.next.value < value){
            cur = cur.next;
        }
        boolean returnValue = cur.next == null || cur.next.value > value;
        lock.readLock().unlock();
        return returnValue;
    }

    public void Insert(int value){
        LinkedList.ListNode node = new LinkedList.ListNode(value);
        if(Find(value))
            return;
        lock.writeLock().lock();
        if(head == null){
            head = node;
            lock.writeLock().unlock();
            return;
        }
        LinkedList.ListNode cur = head;
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
        LinkedList.ListNode cur = head;
        while(cur.next != null && cur.next.value < value){
            cur = cur.next;
        }
        if(cur.next != null){
            cur.next = cur.next.next;
        }
        lock.writeLock().unlock();
    }
}
