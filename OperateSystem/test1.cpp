#include <bits/stdc++.h>
using namespace std;
#define MAXname 100
int n;                //��������
int current_time = 0; //��ǰʱ��
int q = 0;            //�趨��ʱ��Ƭ��С
int t = 0;
struct Process //���̽ṹ�壬��ʾ������Ϣ
{
    string name;         //��������
    int arrive_time;     //����ʱ��
    int service_time;    //��������ʱ��
    int wait_time;       //���̵ȴ�ʱ��
    int remain_time;     //����ʣ������ʱ��
    int turnaround_time; //��תʱ��
    int start_time;      //���̿�ʼ����ʱ��
    int end_time;        //���̽���ʱ��
    int time_slice;      //����ʱ��Ƭ
} run_process, p[MAXname];
queue<Process> ready_queue, block_queue; //����Ϊ�������С���������
bool cmp(Process &a, Process &b)
{
    return a.arrive_time < b.arrive_time;
}
void process_init() //���̳�ʼ��
{
    cout << "�������������" << endl;
    cin >> n;
    cout << "������ʱ��Ƭ����" << endl;
    cin >> q;
    for (int i = 0; i < n; i++)
    {
        cout << "�������" << i + 1 << "�����̵�����  ����ʱ��  ����ʱ��" << endl;
        cin >> p[i].name >> p[i].arrive_time >> p[i].service_time;
        p[i].remain_time = p[i].service_time;
        p[i].time_slice = q; //���ý���ʱ��Ƭ
        p[i].end_time = 0;
    }
    run_process.name = "0"; //��ǰ�޽�������
    sort(p, p + n, cmp);
    for (int i = 0; i < n; i++)
    {
        block_queue.push(p[i]); //�����̼����������У�δ�ﵽ����Ϊ������
    }
}
void nextprocess() //ȡ��һ������
{
    if (!ready_queue.empty()) //���������зǿ�ʱ
    {
        run_process = ready_queue.front(); //ȡ�¸�����
        ready_queue.pop();
    }
    else //�������н�����Ϊ��
        run_process.name = "0";
    run_process.wait_time += current_time - run_process.arrive_time; //����ȴ�ʱ��
}
int block() //���������������������
{
    int a;
    a = rand() % 10;
    return 0;
    if (a >= 0 && a < 3)
    {
        return 1;
    }
    else
        return 0;
}
void process_schedule() //���̵��Ⱥ���
{
    srand(time(NULL)); //���������
    cout << endl
         << "----------------------------------------RR�����㷨----------------------------------------"
         << endl
         << endl;
    cout << "��ǰʱ��  "
         << "��ǰ����  "
         << "���̵���ʱ��  "
         << "���̵ȴ�ʱ��  "
         << "���̷���ʱ��  "
         << "ʣ������ʱ��  "
         << "ʣ��ʱ��Ƭʱ��"
         << endl;
    while (1)
    {
        if (block_queue.empty() && ready_queue.empty() && run_process.name == "0") //���������о�Ϊ��ʱ��˵������ȫ��������
            break;                                                                 //����

        if (!block_queue.empty() && block_queue.front().arrive_time <= current_time)
        {                                                   //�������зǿ��Ҷ���Ԫ�ص���ʱ���ѵ���ǰʱ��
            block_queue.front().arrive_time = current_time; //������������е�ʱ����Ϊ���̵���ʱ�䣨������������Ľ��̣�
            ready_queue.push(block_queue.front());          //������������
            block_queue.pop();                              //����������ɾ��
        }
        if (!ready_queue.empty() && run_process.name == "0") //�������зǿպ����н��̷ǿ�
        {
            run_process = ready_queue.front(); //��Ӿ�������ȡ��Ԫ��
            ready_queue.pop();                 //�Ӿ�������ɾ��
        }
        if (run_process.name == "0") //����ǰ�����н��̣��������
        {
            cout << setw(8) << current_time
                 << setw(10) << run_process.name << endl;
            current_time++;
        }
        else
        { //��ǰ�����н����������Ϣ
            cout << setw(8) << current_time
                 << setw(10) << run_process.name
                 << setw(14) << run_process.arrive_time
                 << setw(14) << run_process.wait_time
                 << setw(14) << run_process.service_time
                 << setw(14) << run_process.remain_time
                 << setw(14) << run_process.time_slice
                 << endl;
            current_time++;            //��ǰʱ���1
            run_process.remain_time--; //����ʣ������ʱ���1
            run_process.time_slice--;  //����ʱ��Ƭʱ���1

            if (run_process.remain_time == 0) //������ʣ������ʱ��Ϊ0
            {
                p[t++] = run_process;
                nextprocess(); //ȡ��һ������
                continue;
            }
            else if (run_process.time_slice == 0) //������ʱ��ƬΪ0ʱ
            {
                run_process.time_slice = q;             //�ָ�ʱ��Ƭ
                run_process.arrive_time = current_time; //���µ���ʱ��
                ready_queue.push(run_process);          //�ٴ����

                nextprocess(); //ȡ��һ������
                continue;
            }
            else if (block()) //������������ʱ���ʱ��Ƭʱ�����ܷ�������
            {
                cout << "-----------------�����������л�����----------------" << endl;
                run_process.arrive_time = current_time; //�������������޸ĵ�ǰ���̵���ʱ��
                block_queue.push(run_process);          //����������������
                nextprocess();
            }
        }
    }
}
void print_process_information() //���������Ϣ
{
    float sumwait = 0;
    cout << "��������  "
         << "����ʱ��  "
         << "�ȴ�ʱ��  "
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(8) << p[i].name
             << setw(10) << p[i].service_time
             << setw(10) << p[i].wait_time
             << endl;
        sumwait += p[i].wait_time;
    }
    cout << "ƽ���ȴ�ʱ��Ϊ��" << setprecision(2) << setiosflags(ios::fixed) << float(sumwait / n) << endl;
}
int main()
{
    process_init();
    process_schedule();
    print_process_information();
    system("pause");
    return 0;
}