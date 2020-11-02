object Form2: TForm2
  Left = 265
  Top = 233
  BorderStyle = bsDialog
  Caption = 'Insert custom message'
  ClientHeight = 246
  ClientWidth = 402
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 56
    Width = 167
    Height = 13
    Caption = 'Checksum will be add automatically'
  end
  object Label2: TLabel
    Left = 16
    Top = 80
    Width = 142
    Height = 13
    Caption = 'Remeber string start = FF FF  !'
  end
  object Edit2: TMemo
    Left = 0
    Top = 112
    Width = 402
    Height = 134
    Align = alBottom
    TabOrder = 0
    OnChange = Edit2Change
    OnDblClick = Edit2DblClick
    OnExit = Edit2Exit
    OnKeyPress = Edit2KeyPress
  end
  object SendBttn: TBitBtn
    Left = 296
    Top = 32
    Width = 75
    Height = 25
    Caption = 'SEND !'
    TabOrder = 1
    OnClick = SendBttnClick
    Kind = bkIgnore
  end
  object CancelBttn: TBitBtn
    Left = 296
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Exit'
    TabOrder = 2
    OnClick = CancelBttnClick
    Kind = bkCancel
  end
  object HexRB: TRadioButton
    Left = 16
    Top = 24
    Width = 57
    Height = 17
    Caption = 'Hex'
    Checked = True
    TabOrder = 3
    TabStop = True
    OnClick = HexRBClick
  end
end
