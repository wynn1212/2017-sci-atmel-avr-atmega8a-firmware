VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "105學年度  工業類科學生技藝競賽  電腦修護職種   第二站  崗位號碼:15          "
   ClientHeight    =   5460
   ClientLeft      =   195
   ClientTop       =   420
   ClientWidth     =   9720
   FillColor       =   &H000000FF&
   FillStyle       =   0  '實心
   BeginProperty Font 
      Name            =   "細明體"
      Size            =   13.5
      Charset         =   136
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H000000FF&
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   5460.387
   ScaleMode       =   0  '使用者自訂
   ScaleWidth      =   9716.548
   StartUpPosition =   2  '螢幕中央
   Begin VB.CommandButton Command3 
      Caption         =   "AVR->PC"
      Height          =   495
      Index           =   1
      Left            =   1920
      TabIndex        =   12
      Top             =   4680
      Width           =   1455
   End
   Begin VB.CommandButton Command3 
      Caption         =   "PC->AVR"
      Height          =   495
      Index           =   0
      Left            =   360
      TabIndex        =   11
      Top             =   4680
      Width           =   1455
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00FFFFFF&
      Caption         =   "K7"
      Height          =   492
      Index           =   7
      Left            =   7920
      Style           =   1  '圖片外觀
      TabIndex        =   9
      Top             =   2496
      Width           =   612
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00C0C000&
      Caption         =   "K6"
      Height          =   492
      Index           =   6
      Left            =   6840
      Style           =   1  '圖片外觀
      TabIndex        =   8
      Top             =   2496
      Width           =   612
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00FF00FF&
      Caption         =   "K5"
      Height          =   492
      Index           =   5
      Left            =   5724
      Style           =   1  '圖片外觀
      TabIndex        =   7
      Top             =   2496
      Width           =   612
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H0000FFFF&
      Caption         =   "K4"
      Height          =   492
      Index           =   4
      Left            =   4680
      Style           =   1  '圖片外觀
      TabIndex        =   6
      Top             =   2496
      Width           =   612
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H00FF0000&
      Caption         =   "K3"
      Height          =   492
      Index           =   3
      Left            =   3516
      Style           =   1  '圖片外觀
      TabIndex        =   5
      Top             =   2496
      Width           =   612
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H0000FF00&
      Caption         =   "K2"
      Height          =   492
      Index           =   2
      Left            =   2424
      Style           =   1  '圖片外觀
      TabIndex        =   4
      Top             =   2496
      Width           =   612
   End
   Begin VB.CommandButton Command2 
      BackColor       =   &H000000FF&
      Caption         =   "K1"
      Height          =   492
      Index           =   1
      Left            =   1320
      Style           =   1  '圖片外觀
      TabIndex        =   3
      Top             =   2496
      Width           =   612
   End
   Begin VB.Timer Timer1 
      Interval        =   10
      Left            =   120
      Top             =   120
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H00FFFFFF&
      Caption         =   "EXIT"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   18
         Charset         =   136
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   510
      Index           =   1
      Left            =   6480
      Style           =   1  '圖片外觀
      TabIndex        =   0
      Top             =   4680
      Width           =   2200
   End
   Begin VB.Label Label6 
      BorderStyle     =   1  '單線固定
      Caption         =   "Label6"
      Height          =   375
      Left            =   2280
      TabIndex        =   15
      Top             =   4200
      Width           =   1935
   End
   Begin VB.Label Label5 
      Caption         =   "時間同步選項"
      Height          =   375
      Left            =   360
      TabIndex        =   14
      Top             =   4200
      Width           =   1815
   End
   Begin VB.Label Label3 
      BorderStyle     =   1  '單線固定
      Height          =   615
      Left            =   7560
      TabIndex        =   13
      Top             =   3240
      Width           =   1935
   End
   Begin VB.Label Label2 
      BorderStyle     =   1  '單線固定
      Caption         =   "ON LINE"
      BeginProperty Font 
         Name            =   "細明體"
         Size            =   12
         Charset         =   136
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   240
      TabIndex        =   10
      Top             =   3240
      Width           =   7095
   End
   Begin VB.Label Label4 
      Caption         =   "RGB"
      Height          =   372
      Index           =   0
      Left            =   1440
      TabIndex        =   2
      Top             =   1800
      Width           =   492
   End
   Begin VB.Label Label1 
      Alignment       =   2  '置中對齊
      BorderStyle     =   1  '單線固定
      Caption         =   "ON LINE"
      BeginProperty Font 
         Name            =   "細明體"
         Size            =   48
         Charset         =   136
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1092
      Left            =   2520
      TabIndex        =   1
      Top             =   600
      Width           =   6012
   End
   Begin VB.Shape ff 
      FillStyle       =   0  '實心
      Height          =   852
      Left            =   1320
      Shape           =   3  '圓形
      Top             =   720
      Width           =   732
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Dim VBKEY, fr, c, hour, min, sec, shour, smin, ssec As Integer
Dim chkdata(10) As Byte
Dim datain(10) As Byte
Dim bRun, ready As Boolean

Private Sub Command1_Click(Index As Integer)
    Unload Forms(0)
End Sub

Private Sub Command2_Click(Index As Integer)
    VBKEY = Index
    c = 0
    'If VBKEY = 1 Then
    'If VBKEY = 1 Then fr = 262: ff.FillColor = vbRed
    'If VBKEY = 1 Then bRun = bRun Xor True
    'If VBKEY = 2 Then fr = 330: ff.FillColor = vbGreen
    'If VBKEY = 2 Then shour = hour: smin = min: ssec = sec
    'If VBKEY = 2 Then bRun = bRun Xor True
    'If VBKEY = 3 Then fr = 262: ff.FillColor = vbBlue
    'If VBKEY = 4 Then fr = 330: ff.FillColor = vbYellow
    'If VBKEY = 5 Then fr = 262: ff.FillColor = RGB(255, 0, 255)
    'If VBKEY = 6 Then fr = 330: ff.FillColor = RGB(0, 255, 255)
    'If VBKEY = 7 Then fr = 262: ff.FillColor = vbWhite
    Timer1.Enabled = False
End Sub

Private Sub Command3_Click(Index As Integer)
    If (Index = 0) Then
        hour = Val(Mid(Time$, 1, 2))
        min = Val(Mid(Time$, 4, 2))
        sec = Val(Mid(Time$, 7, 2))
        Call USBfunc("clock", True)
    ElseIf (Index = 1) Then
        Dim rhour, rmin, rsec As Integer
        Call USBfunc("clock", False)
        Label6.Caption = ""
        rhour = datain(6)
        rmin = datain(7)
        rsec = datain(8)
        Label6.Caption = Format(rhour, "00") & ":" & Format(rmin, "00") & ":" & Format(rsec, "00")
    End If
End Sub

Private Sub Form_Initialize()
    ready = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    On Error GoTo errHandler
    DoEvents
    If OpenUsbDevice(&H1234, &H2468) Then
        OutDataEightByte 0, &H3, 0, 0, 0, 0, 0, 0
        CloseUsbDevice
    End If
    Timer1.Enabled = True ': Timer2.Enabled = False
    Exit Sub
errHandler:
    Timer1.Enabled = False ': Timer2.Enabled = False
       Label1.Caption = "OFF LINE"
       ff.FillStyle = 1
    Unload Forms(0)
End Sub

Private Sub USBfunc(ByVal mode As String, ByVal IsWrite As Boolean)
    Dim ack1, ack2, ack3, ack4 As Boolean
    If OpenUsbDevice(&H1234, &H2468) Then
        If ready = True Then
            If IsWrite = True Then
                '      (index)    0   1     2       3        4       5     6  7
                'OutDataEightByte 0, &H4, VBKEY, fr / 10, fr Mod 10, bRun, 0, 0
                If (mode = "clock") Then
                    ready = 0
                    OutDataEightByte 0, &H1, 0, 0, 0, hour, min, sec
                ElseIf (mode = "key") Then
                    ready = 0
                    OutDataEightByte 0, &H1, 0, 0, 0, shour, smin, ssec 'Not Done
                ElseIf (mode = "led") Then
                    ready = 0
                    OutDataEightByte 0, &H1, 0, 0, 0, shour, smin, ssec 'Not Done
                Else
                    MsgBox ("Illegial Instruction, Invaild Operation")
                End If
                CloseUsbDevice
            Else
                If (mode = "clock") Then
                    ready = 0
                    OutDataEightByte 0, &H2, 0, 0, 0, 0, 0, 0
                    CloseUsbDevice
                    ReadData datain
                    Label2.Caption = ""     'Clear Label2.Caption
                    For i = 0 To 8: Label2.Caption = Label2.Caption & datain(i): Next i
                    CloseUsbDevice
                ElseIf (mode = "key") Then
                    
                ElseIf (mode = "led") Then
                    
                Else
                    Label2.Caption = ""     'Clear Label2.Caption
                    ReadData datain
                    For i = 0 To 8: Label2.Caption = Label2.Caption & datain(i): Next i
                    CloseUsbDevice
                    Label1.Caption = "ON LINE"
                    ff.FillStyle = 0
                End If
            End If
        End If
    Else
                    Label1.Caption = "OFF LINE"
                    ff.FillStyle = 1
    End If
End Sub

Private Sub USBCheck()
    If (OpenUsbDevice(&H1234, &H2468)) Then
        ReadData chkdata
        CloseUsbDevice
        For i = 0 To 7
            If (chkdata(i) = 5) Then
                ready = 1
                For j = 0 To 10: chkdata(i) = 0: Next j
            End If
        Next i
    End If
End Sub


Private Sub Timer1_Timer()                             ''讀取KEY
    DoEvents
    On Error GoTo errHandler
    frmMain.Caption = Time$ + "  V1.2-2017-Jan-01  "
    Call USBfunc(other, False)
    Call USBCheck
    If (ready = False) Then
        Label3.Caption = "BUSY"
    Else
        Label3.Caption = "READY"
    End If
    Exit Sub
errHandler:
    Timer1.Enabled = False
       Label1.Caption = "OFF LINE"
       ff.FillStyle = 1
    Unload Forms(0)
End Sub

