using System;
using System.Net;
using System.Net.Sockets;
using System.IO;
using UnityEngine;

public class PlatformInterface: MonoBehaviour
{

    // Network configurations

    private bool connected;
    // [SerializeField] private bool toConnect = true;
    private TcpClient client;
    private NetworkStream ns;
    // private StreamReader reader;
    [SerializeField] private string IP = "127.0.0.1";   //TODO: NAO ESTAR HARDCODED? UI?
    [SerializeField] private int PORT = 55001;
    // private IPAddress ipAddr = IPAddress.Parse(IP);

    void Start(){
    }

    public bool ConnectToPlatform()
    {
        client = new TcpClient();
        try
        {
            client.Connect(IP, PORT);
            ns = client.GetStream();
            // reader = new StreamReader(ns);
            connected = true;
            Debug.Log("Connected");
        }
        catch (SocketException e)
        {
            connected = false;
            Debug.Log("Could not connect");
        }
        return connected;
    }

    public bool IsConnected(){
        return connected;
    }

    public void SendData(float[] points)
    {
        byte[] data = new byte[points.Length * sizeof(float)];
        int dataIndex = 0;
        foreach (float el in points)
        {
            byte[] bytes = BitConverter.GetBytes(el);
            for (int i = 0; i < sizeof(float); i++) data[dataIndex++] = bytes[i];
        }

        ns.Write(data, 0, data.Length);
    }
    
}
