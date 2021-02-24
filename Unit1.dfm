object Form1: TForm1
  Left = 264
  Top = 103
  Width = 700
  Height = 577
  Caption = 'Emulator machine 0.80'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnConstrainedResize = FormConstrainedResize
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 332
    Top = 4
    Width = 54
    Height = 13
    Caption = 'COM port'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object SpeedButton3: TSpeedButton
    Left = 593
    Top = 8
    Width = 23
    Height = 22
    Caption = 'R'
    OnClick = SpeedButton3Click
  end
  object ConnectLabel: TLabel
    Left = 429
    Top = 12
    Width = 49
    Height = 13
    Caption = 'Transmit'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 504
    Top = 8
    Width = 32
    Height = 13
    Caption = 'Label2'
    Visible = False
  end
  object SerialSelectCB: TComboBox
    Left = 2
    Top = 7
    Width = 321
    Height = 21
    BiDiMode = bdLeftToRight
    ItemHeight = 13
    ItemIndex = 0
    ParentBiDiMode = False
    TabOrder = 0
    Text = '0 - None'
    OnChange = SerialSelectCBChange
    Items.Strings = (
      '0 - None')
  end
  object LiveRB: TRadioButton
    Left = 345
    Top = 19
    Width = 17
    Height = 17
    TabOrder = 1
  end
  object RichEdit1: TRichEdit
    Left = 2
    Top = 39
    Width = 558
    Height = 477
    Hint = 'Receive window'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    PopupMenu = PopupMenu1
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 3
    OnChange = RichEdit1Change
  end
  object StaticText6: TStaticText
    Left = 120
    Top = 117
    Width = 96
    Height = 17
    Caption = 'New serialport timer'
    TabOrder = 2
    Visible = False
  end
  object Panel2: TPanel
    Left = 563
    Top = 41
    Width = 116
    Height = 473
    TabOrder = 4
    object Panel1: TPanel
      Left = 13
      Top = 4
      Width = 89
      Height = 105
      Enabled = False
      TabOrder = 0
      object ConfigRequestBttn: TBitBtn
        Left = 7
        Top = 11
        Width = 75
        Height = 25
        Caption = 'Config [F2]'
        TabOrder = 0
        OnClick = ConfigRequestBttnClick
      end
      object F2_SentCKB: TDBCheckBox
        Left = 11
        Top = 51
        Width = 49
        Height = 17
        Caption = 'Sent'
        ReadOnly = True
        TabOrder = 1
        ValueChecked = 'True'
        ValueUnchecked = 'False'
      end
      object F2GotAnswerCKB: TDBCheckBox
        Left = 11
        Top = 75
        Width = 63
        Height = 17
        Caption = 'Answer'
        ReadOnly = True
        TabOrder = 2
        ValueChecked = 'True'
        ValueUnchecked = 'False'
      end
    end
    object DeviceComboBox: TComboBox
      Left = 3
      Top = 124
      Width = 109
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = 'WC'
      OnChange = DeviceComboBoxChange
      Items.Strings = (
        'WC'
        'WH'
        'HVAC'
        'HVAC II'
        'WM'
        'FR-RU60cm'
        'Hood Arcair'
        'Hood Haier'
        'FR-MultiD k A3FE'
        'FR-MultiD j HB20')
    end
    object CustomMsgBttn: TButton
      Left = 15
      Top = 184
      Width = 86
      Height = 25
      Caption = 'Custom MSG'
      TabOrder = 2
      OnClick = CustomMsgBttnClick
    end
    object WriteLogPopMnu: TCheckBox
      Left = 15
      Top = 261
      Width = 71
      Height = 17
      Caption = 'Write Log'
      TabOrder = 3
      OnClick = WriteLogPopMnuClick
    end
    object SendAnswerPopMnu: TCheckBox
      Left = 15
      Top = 286
      Width = 85
      Height = 17
      Caption = 'Send Answer'
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object Edit1: TEdit
      Left = 13
      Top = 315
      Width = 89
      Height = 21
      TabOrder = 5
      Text = 'Edit1'
      Visible = False
    end
    object Panel3: TPanel
      Left = 13
      Top = 342
      Width = 90
      Height = 83
      TabOrder = 6
      object Label1: TLabel
        Left = 65
        Top = 10
        Width = 15
        Height = 13
        Caption = '0.0'
      end
      object Button2: TButton
        Left = 3
        Top = 32
        Width = 83
        Height = 25
        Caption = 'Force status'
        TabOrder = 0
        OnClick = Button2Click
      end
      object StatusCKB: TCheckBox
        Left = 5
        Top = 8
        Width = 43
        Height = 17
        Caption = 'Auto'
        TabOrder = 1
      end
    end
    object ExitBttn: TButton
      Left = 16
      Top = 437
      Width = 87
      Height = 25
      Caption = '&Quit'
      TabOrder = 7
      OnClick = ExitBttnClick
    end
    object AlarmBttn: TButton
      Left = 15
      Top = 213
      Width = 86
      Height = 25
      Caption = 'Alarms ...'
      TabOrder = 8
      OnClick = AlarmBttnClick
    end
    object BitBtn1: TBitBtn
      Left = 15
      Top = 152
      Width = 86
      Height = 25
      Caption = 'Type ID    '
      TabOrder = 9
      OnClick = BitBtn1Click
      Kind = bkHelp
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 519
    Width = 684
    Height = 19
    Panels = <
      item
        Width = 70
      end
      item
        Width = 250
      end
      item
        Width = 160
      end
      item
        Width = 100
      end>
    SimplePanel = False
    OnDblClick = StatusBar1DblClick
  end
  object CB_Connect: TdxfCheckBox
    Left = 399
    Top = 5
    Width = 24
    Height = 30
    Hint = 'Stato Richiesta'
    Checked = False
    GroupIndex = 0
    GlyphChecked.Data = {
      DE010000424DDE010000000000007600000028000000140000001E0000000100
      0400000000006801000000000000000000001000000000000000000000000000
      8000008000000080800080000000800080008080000080808000C0C0C0000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00DDDDDDDDDDDD
      DDDDDDDD0000DDDDDDDDDDDDDDDDDDDD0000DDDDDDDDDDDDDDDDDDDD0000DDDD
      D000000000000DDD0000DDDD0777777777700DDD0000DDD00000000000070DDD
      0000DDD0FFFFFFFFFF070DDD0000DDD0FFFFFFFFFF070DDD0000DDD0FFF2222F
      FF070DDD0000DDD0FF2AAAA2FF070DDD0000DDD0FF2AAAA2FF070DDD0000DDD0
      FFF2222FFF070DDD0000DDD0FFFFFFFFFF070DDD0000DDD0FFFFFFFFFF070DDD
      0000DDD00000000000070DDD0000DDD08888888888070DDD0000DD0888888888
      80770DDD0000DD088888888880770DDD0000DD088888888880770DDD0000D088
      8888888807770DDD0000D0888888888807770DDD0000D0FFFFFFFFFF07770DDD
      0000D0FFFFFFFFFF07770DDD0000DD0FFFFFFFFFF0770DDD0000DDD0FFFFFFFF
      FF000DDD0000DDDD0000000000000DDD0000DDDDDDDDDDDDDDDDDDDD0000DDDD
      DDDDDDDDDDDDDDDD0000DDDDDDDDDDDDDDDDDDDD0000DDDDDDDDDDDDDDDDDDDD
      0000}
    GlyphUnChecked.Data = {
      3E070000424D3E070000000000003600000028000000140000001E0000000100
      1800000000000807000000000000000000000000000000000000FF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF00000000000000000000
      0000000000000000000000000000000000000000000000000000000000FF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000808080000000FF00FFFF00FFFF
      00FFFF00FFFF00FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0000000808080808080000000FF00FFFF00FFFF00FFFF00
      FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0000000808080808080808080000000FF00FFFF00FFFF00FFFF00FF000000
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000
      00808080808080808080000000FF00FFFF00FFFF00FFFF00FF000000FFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000808080
      808080808080000000FF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000080808080808080
      8080000000FF00FFFF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000008080808080800000
      00FF00FFFF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000808080808080000000FF00FF
      FF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFF000000808080808080000000FF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFF000000808080000000FF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FF00000000000000000000000000000000000000000000000000
      0000000000000000000000808080000000FF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFF000000808080000000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF00
      0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      000000808080000000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF000000FFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000080
      8080000000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000008080800000
      00FF00FFFF00FFFF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000808080000000FF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000808080000000FF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFF000000808080000000FF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFF000000808080000000FF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FF0000000000000000000000000000000000000000000000000000000000
      00000000000000808080000000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FF000000808080808080808080808080808080808080808080808080808080
      808080000000000000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FF
      FF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
      FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF
      00FF}
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 6
    Visible = False
    OnClick = CB_ConnectClick
  end
  object NewSerialTimer: TTimer
    Interval = 2000
    OnTimer = NewSerialTimerTimer
    Left = 80
    Top = 112
  end
  object PopupMenu1: TPopupMenu
    Left = 120
    Top = 192
    object Frame09force1: TMenuItem
      Caption = '09 Stop Alarm frame'
      Enabled = False
      OnClick = Frame09force1Click
    end
    object N7CSetreportinterval1: TMenuItem
      Caption = '7C Set report interval'
      Enabled = False
      Visible = False
      OnClick = N7CSetreportinterval1Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object PrintRTF1: TMenuItem
      Caption = 'Print RTF'
      OnClick = PrintRTF1Click
    end
    object Clean1: TMenuItem
      Caption = 'Clean'
      OnClick = Clean1Click
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object Predictive1: TMenuItem
      Caption = 'Predictive'
      OnClick = Predictive1Click
    end
  end
end
