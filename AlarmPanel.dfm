object Form3: TForm3
  Left = 230
  Top = 125
  BorderIcons = [biSystemMenu, biMaximize]
  BorderStyle = bsDialog
  Caption = 'Alarm'
  ClientHeight = 218
  ClientWidth = 386
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 183
    Top = 187
    Width = 22
    Height = 13
    Caption = 'HEX'
  end
  object Label2: TLabel
    Left = 16
    Top = 6
    Width = 39
    Height = 13
    Caption = 'Label2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 88
    Width = 32
    Height = 13
    Caption = 'Label3'
    Visible = False
  end
  object SpeedButton1: TSpeedButton
    Left = 0
    Top = 187
    Width = 23
    Height = 22
    OnClick = SpeedButton1Click
  end
  object Edit1: TEdit
    Left = 5
    Top = 62
    Width = 25
    Height = 21
    TabOrder = 0
    Visible = False
    OnChange = Edit1Change
    OnEnter = Edit1Enter
  end
  object ClearBttn: TButton
    Left = 16
    Top = 123
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 1
    OnClick = ClearBttnClick
  end
  object NextBitBttn: TBitBtn
    Left = 296
    Top = 123
    Width = 75
    Height = 25
    Caption = 'Next'
    TabOrder = 2
    OnClick = NextBitBttnClick
    Kind = bkRetry
  end
  object AlrmComboBox: TComboBox
    Left = 24
    Top = 158
    Width = 233
    Height = 21
    ItemHeight = 13
    TabOrder = 3
    OnChange = AlrmComboBoxChange
  end
  object EnterBitBttn: TBitBtn
    Left = 152
    Top = 123
    Width = 65
    Height = 25
    Caption = 'Enter'
    TabOrder = 4
    OnClick = EnterBitBttnClick
    Kind = bkOK
  end
  object StaticText1: TStaticText
    Left = 13
    Top = 41
    Width = 10
    Height = 17
    Caption = '0'
    TabOrder = 5
    Visible = False
  end
end
