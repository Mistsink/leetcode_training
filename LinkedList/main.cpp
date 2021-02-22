#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

ListNode* createLinkedList (int arr[], int length) {
    if (length == 0) return NULL;

    ListNode* head = new ListNode(arr[0]), *cur = head;

    for (int i = 1; i < length; i ++) {
        cur->next = new ListNode(arr[i]);
        cur = cur->next;
    }

    return head;
}

void printLinkedList(ListNode* head) {
    ListNode *cur = head;
    while (cur != NULL) {
        cout << cur->val << " -> ";
        cur = cur->next;
    }

    cout << "NULL" << endl;
}

void deleteLinkedList (ListNode* head) {
    ListNode* cur = head, *delNode = NULL;

    while (cur != NULL) {
        delNode = cur;
        cur = cur->next;
        delete delNode;
    }
}


class Solution {
public:
    /**
     * 206. 反转链表
     */
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = NULL, *cur = head, *next = NULL;

        while (cur != NULL) {
            next = cur->next;

            cur->next = pre;
            pre = cur;
            cur = next;
        }

        return pre;
    }



    /**
     * 203. 移除链表元素
     */
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(), *delNode = NULL, *cur;
        dummyHead->next = head;
        cur = dummyHead;
        while (cur != NULL) {
            if (cur->next != NULL && cur->next->val == val) {
                delNode = cur->next;
                cur->next = delNode->next;
                delete delNode;
            }
            else
                cur = cur->next;
        }

        return dummyHead->next;
    }

    /**
     * 24. 两两交换链表中的节点
     */
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;

        ListNode *pre = dummyHead, *node1, *node2, *next;

        while (pre->next && pre->next->next) {
            node1 = pre->next;
            node2 = node1->next;
            next = node2->next;

            pre->next = node2;
            node2->next = node1;
            node1->next = next;

            pre = node1;        // 此时node1为靠后的节点
        }

        return dummyHead->next;
    }


    /**
     * 237. 删除链表中的节点
     */
    void deleteNode(ListNode* node) {
        if (!node) {
            return;
        }

        if(!node->next) {
            delete node;
            node = NULL;
            return;
        }

        ListNode* next = node->next;
        node->val = next->val;
        node->next = next->next;
        delete next;
    }


    /**
     * 19. 删除链表的倒数第 N 个结点
     */
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;

        ListNode* p = dummyHead, *q = dummyHead;
        for (int i =0; i < n +1; i ++) {
            assert(q);
            q = q->next;
        }

        while (q != NULL) {
            p = p->next;
            q = q->next;
        }
        ListNode* del = p->next;
        p->next = del->next;
        delete del;

        return dummyHead->next;
    }
};


int main() {

    int arr[] = {1,2,6,3,4,5,6};
    ListNode* head1 = createLinkedList(arr, sizeof(arr)/ sizeof(arr[0]));
    printLinkedList(head1);
    ListNode* head2 = Solution().removeElements(head1, 6);
    printLinkedList(head2);
    return 0;
}
