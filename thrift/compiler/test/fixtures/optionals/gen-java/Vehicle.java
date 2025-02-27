/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;
import java.util.Collections;
import java.util.BitSet;
import java.util.Arrays;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.facebook.thrift.*;
import com.facebook.thrift.async.*;
import com.facebook.thrift.meta_data.*;
import com.facebook.thrift.server.*;
import com.facebook.thrift.transport.*;
import com.facebook.thrift.protocol.*;

@SuppressWarnings({ "unused", "serial" })
public class Vehicle implements TBase, java.io.Serializable, Cloneable, Comparable<Vehicle> {
  private static final TStruct STRUCT_DESC = new TStruct("Vehicle");
  private static final TField COLOR_FIELD_DESC = new TField("color", TType.STRUCT, (short)1);
  private static final TField LICENSE_PLATE_FIELD_DESC = new TField("licensePlate", TType.STRING, (short)2);
  private static final TField DESCRIPTION_FIELD_DESC = new TField("description", TType.STRING, (short)3);
  private static final TField NAME_FIELD_DESC = new TField("name", TType.STRING, (short)4);
  private static final TField HAS_AC_FIELD_DESC = new TField("hasAC", TType.BOOL, (short)5);

  public Color color;
  public String licensePlate;
  public String description;
  public String name;
  public boolean hasAC;
  public static final int COLOR = 1;
  public static final int LICENSEPLATE = 2;
  public static final int DESCRIPTION = 3;
  public static final int NAME = 4;
  public static final int HASAC = 5;
  public static boolean DEFAULT_PRETTY_PRINT = true;

  // isset id assignments
  private static final int __HASAC_ISSET_ID = 0;
  private BitSet __isset_bit_vector = new BitSet(1);

  public static final Map<Integer, FieldMetaData> metaDataMap;
  static {
    Map<Integer, FieldMetaData> tmpMetaDataMap = new HashMap<Integer, FieldMetaData>();
    tmpMetaDataMap.put(COLOR, new FieldMetaData("color", TFieldRequirementType.DEFAULT, 
        new StructMetaData(TType.STRUCT, Color.class)));
    tmpMetaDataMap.put(LICENSEPLATE, new FieldMetaData("licensePlate", TFieldRequirementType.OPTIONAL, 
        new FieldValueMetaData(TType.STRING)));
    tmpMetaDataMap.put(DESCRIPTION, new FieldMetaData("description", TFieldRequirementType.OPTIONAL, 
        new FieldValueMetaData(TType.STRING)));
    tmpMetaDataMap.put(NAME, new FieldMetaData("name", TFieldRequirementType.OPTIONAL, 
        new FieldValueMetaData(TType.STRING)));
    tmpMetaDataMap.put(HASAC, new FieldMetaData("hasAC", TFieldRequirementType.OPTIONAL, 
        new FieldValueMetaData(TType.BOOL)));
    metaDataMap = Collections.unmodifiableMap(tmpMetaDataMap);
  }

  static {
    FieldMetaData.addStructMetaDataMap(Vehicle.class, metaDataMap);
  }

  public Vehicle() {
    this.hasAC = false;

  }

  public Vehicle(
    Color color)
  {
    this();
    this.color = color;
  }

  public Vehicle(
    Color color,
    String licensePlate,
    String description,
    String name,
    boolean hasAC)
  {
    this();
    this.color = color;
    this.licensePlate = licensePlate;
    this.description = description;
    this.name = name;
    this.hasAC = hasAC;
    setHasACIsSet(true);
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public Vehicle(Vehicle other) {
    __isset_bit_vector.clear();
    __isset_bit_vector.or(other.__isset_bit_vector);
    if (other.isSetColor()) {
      this.color = TBaseHelper.deepCopy(other.color);
    }
    if (other.isSetLicensePlate()) {
      this.licensePlate = TBaseHelper.deepCopy(other.licensePlate);
    }
    if (other.isSetDescription()) {
      this.description = TBaseHelper.deepCopy(other.description);
    }
    if (other.isSetName()) {
      this.name = TBaseHelper.deepCopy(other.name);
    }
    this.hasAC = TBaseHelper.deepCopy(other.hasAC);
  }

  public Vehicle deepCopy() {
    return new Vehicle(this);
  }

  @Deprecated
  public Vehicle clone() {
    return new Vehicle(this);
  }

  public Color getColor() {
    return this.color;
  }

  public Vehicle setColor(Color color) {
    this.color = color;
    return this;
  }

  public void unsetColor() {
    this.color = null;
  }

  // Returns true if field color is set (has been assigned a value) and false otherwise
  public boolean isSetColor() {
    return this.color != null;
  }

  public void setColorIsSet(boolean value) {
    if (!value) {
      this.color = null;
    }
  }

  public String getLicensePlate() {
    return this.licensePlate;
  }

  public Vehicle setLicensePlate(String licensePlate) {
    this.licensePlate = licensePlate;
    return this;
  }

  public void unsetLicensePlate() {
    this.licensePlate = null;
  }

  // Returns true if field licensePlate is set (has been assigned a value) and false otherwise
  public boolean isSetLicensePlate() {
    return this.licensePlate != null;
  }

  public void setLicensePlateIsSet(boolean value) {
    if (!value) {
      this.licensePlate = null;
    }
  }

  public String getDescription() {
    return this.description;
  }

  public Vehicle setDescription(String description) {
    this.description = description;
    return this;
  }

  public void unsetDescription() {
    this.description = null;
  }

  // Returns true if field description is set (has been assigned a value) and false otherwise
  public boolean isSetDescription() {
    return this.description != null;
  }

  public void setDescriptionIsSet(boolean value) {
    if (!value) {
      this.description = null;
    }
  }

  public String getName() {
    return this.name;
  }

  public Vehicle setName(String name) {
    this.name = name;
    return this;
  }

  public void unsetName() {
    this.name = null;
  }

  // Returns true if field name is set (has been assigned a value) and false otherwise
  public boolean isSetName() {
    return this.name != null;
  }

  public void setNameIsSet(boolean value) {
    if (!value) {
      this.name = null;
    }
  }

  public boolean isHasAC() {
    return this.hasAC;
  }

  public Vehicle setHasAC(boolean hasAC) {
    this.hasAC = hasAC;
    setHasACIsSet(true);
    return this;
  }

  public void unsetHasAC() {
    __isset_bit_vector.clear(__HASAC_ISSET_ID);
  }

  // Returns true if field hasAC is set (has been assigned a value) and false otherwise
  public boolean isSetHasAC() {
    return __isset_bit_vector.get(__HASAC_ISSET_ID);
  }

  public void setHasACIsSet(boolean value) {
    __isset_bit_vector.set(__HASAC_ISSET_ID, value);
  }

  public void setFieldValue(int fieldID, Object value) {
    switch (fieldID) {
    case COLOR:
      if (value == null) {
        unsetColor();
      } else {
        setColor((Color)value);
      }
      break;

    case LICENSEPLATE:
      if (value == null) {
        unsetLicensePlate();
      } else {
        setLicensePlate((String)value);
      }
      break;

    case DESCRIPTION:
      if (value == null) {
        unsetDescription();
      } else {
        setDescription((String)value);
      }
      break;

    case NAME:
      if (value == null) {
        unsetName();
      } else {
        setName((String)value);
      }
      break;

    case HASAC:
      if (value == null) {
        unsetHasAC();
      } else {
        setHasAC((Boolean)value);
      }
      break;

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  public Object getFieldValue(int fieldID) {
    switch (fieldID) {
    case COLOR:
      return getColor();

    case LICENSEPLATE:
      return getLicensePlate();

    case DESCRIPTION:
      return getDescription();

    case NAME:
      return getName();

    case HASAC:
      return new Boolean(isHasAC());

    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  // Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise
  public boolean isSet(int fieldID) {
    switch (fieldID) {
    case COLOR:
      return isSetColor();
    case LICENSEPLATE:
      return isSetLicensePlate();
    case DESCRIPTION:
      return isSetDescription();
    case NAME:
      return isSetName();
    case HASAC:
      return isSetHasAC();
    default:
      throw new IllegalArgumentException("Field " + fieldID + " doesn't exist!");
    }
  }

  @Override
  public boolean equals(Object that) {
    if (that == null)
      return false;
    if (that instanceof Vehicle)
      return this.equals((Vehicle)that);
    return false;
  }

  public boolean equals(Vehicle that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_color = true && this.isSetColor();
    boolean that_present_color = true && that.isSetColor();
    if (this_present_color || that_present_color) {
      if (!(this_present_color && that_present_color))
        return false;
      if (!TBaseHelper.equalsNobinary(this.color, that.color))
        return false;
    }

    boolean this_present_licensePlate = true && this.isSetLicensePlate();
    boolean that_present_licensePlate = true && that.isSetLicensePlate();
    if (this_present_licensePlate || that_present_licensePlate) {
      if (!(this_present_licensePlate && that_present_licensePlate))
        return false;
      if (!TBaseHelper.equalsNobinary(this.licensePlate, that.licensePlate))
        return false;
    }

    boolean this_present_description = true && this.isSetDescription();
    boolean that_present_description = true && that.isSetDescription();
    if (this_present_description || that_present_description) {
      if (!(this_present_description && that_present_description))
        return false;
      if (!TBaseHelper.equalsNobinary(this.description, that.description))
        return false;
    }

    boolean this_present_name = true && this.isSetName();
    boolean that_present_name = true && that.isSetName();
    if (this_present_name || that_present_name) {
      if (!(this_present_name && that_present_name))
        return false;
      if (!TBaseHelper.equalsNobinary(this.name, that.name))
        return false;
    }

    boolean this_present_hasAC = true && this.isSetHasAC();
    boolean that_present_hasAC = true && that.isSetHasAC();
    if (this_present_hasAC || that_present_hasAC) {
      if (!(this_present_hasAC && that_present_hasAC))
        return false;
      if (!TBaseHelper.equalsNobinary(this.hasAC, that.hasAC))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    return 0;
  }

  @Override
  public int compareTo(Vehicle other) {
    if (other == null) {
      // See java.lang.Comparable docs
      throw new NullPointerException();
    }

    if (other == this) {
      return 0;
    }
    int lastComparison = 0;

    lastComparison = Boolean.valueOf(isSetColor()).compareTo(other.isSetColor());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(color, other.color);
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = Boolean.valueOf(isSetLicensePlate()).compareTo(other.isSetLicensePlate());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(licensePlate, other.licensePlate);
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = Boolean.valueOf(isSetDescription()).compareTo(other.isSetDescription());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(description, other.description);
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = Boolean.valueOf(isSetName()).compareTo(other.isSetName());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(name, other.name);
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = Boolean.valueOf(isSetHasAC()).compareTo(other.isSetHasAC());
    if (lastComparison != 0) {
      return lastComparison;
    }
    lastComparison = TBaseHelper.compareTo(hasAC, other.hasAC);
    if (lastComparison != 0) {
      return lastComparison;
    }
    return 0;
  }

  public void read(TProtocol iprot) throws TException {
    TField field;
    iprot.readStructBegin(metaDataMap);
    while (true)
    {
      field = iprot.readFieldBegin();
      if (field.type == TType.STOP) { 
        break;
      }
      switch (field.id)
      {
        case COLOR:
          if (field.type == TType.STRUCT) {
            this.color = new Color();
            this.color.read(iprot);
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case LICENSEPLATE:
          if (field.type == TType.STRING) {
            this.licensePlate = iprot.readString();
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case DESCRIPTION:
          if (field.type == TType.STRING) {
            this.description = iprot.readString();
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case NAME:
          if (field.type == TType.STRING) {
            this.name = iprot.readString();
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        case HASAC:
          if (field.type == TType.BOOL) {
            this.hasAC = iprot.readBool();
            setHasACIsSet(true);
          } else { 
            TProtocolUtil.skip(iprot, field.type);
          }
          break;
        default:
          TProtocolUtil.skip(iprot, field.type);
          break;
      }
      iprot.readFieldEnd();
    }
    iprot.readStructEnd();


    // check for required fields of primitive type, which can't be checked in the validate method
    validate();
  }

  public void write(TProtocol oprot) throws TException {
    validate();

    oprot.writeStructBegin(STRUCT_DESC);
    if (this.color != null) {
      oprot.writeFieldBegin(COLOR_FIELD_DESC);
      this.color.write(oprot);
      oprot.writeFieldEnd();
    }
    if (this.licensePlate != null) {
      if (isSetLicensePlate()) {
        oprot.writeFieldBegin(LICENSE_PLATE_FIELD_DESC);
        oprot.writeString(this.licensePlate);
        oprot.writeFieldEnd();
      }
    }
    if (this.description != null) {
      if (isSetDescription()) {
        oprot.writeFieldBegin(DESCRIPTION_FIELD_DESC);
        oprot.writeString(this.description);
        oprot.writeFieldEnd();
      }
    }
    if (this.name != null) {
      if (isSetName()) {
        oprot.writeFieldBegin(NAME_FIELD_DESC);
        oprot.writeString(this.name);
        oprot.writeFieldEnd();
      }
    }
    if (isSetHasAC()) {
      oprot.writeFieldBegin(HAS_AC_FIELD_DESC);
      oprot.writeBool(this.hasAC);
      oprot.writeFieldEnd();
    }
    oprot.writeFieldStop();
    oprot.writeStructEnd();
  }

  @Override
  public String toString() {
    return toString(DEFAULT_PRETTY_PRINT);
  }

  @Override
  public String toString(boolean prettyPrint) {
    return toString(1, prettyPrint);
  }

  @Override
  public String toString(int indent, boolean prettyPrint) {
    String indentStr = prettyPrint ? TBaseHelper.getIndentedString(indent) : "";
    String newLine = prettyPrint ? "\n" : "";
    String space = prettyPrint ? " " : "";
    StringBuilder sb = new StringBuilder("Vehicle");
    sb.append(space);
    sb.append("(");
    sb.append(newLine);
    boolean first = true;

    sb.append(indentStr);
    sb.append("color");
    sb.append(space);
    sb.append(":").append(space);
    if (this.getColor() == null) {
      sb.append("null");
    } else {
      sb.append(TBaseHelper.toString(this.getColor(), indent + 1, prettyPrint));
    }
    first = false;
    if (isSetLicensePlate())
    {
      if (!first) sb.append("," + newLine);
      sb.append(indentStr);
      sb.append("licensePlate");
      sb.append(space);
      sb.append(":").append(space);
      if (this.getLicensePlate() == null) {
        sb.append("null");
      } else {
        sb.append(TBaseHelper.toString(this.getLicensePlate(), indent + 1, prettyPrint));
      }
      first = false;
    }
    if (isSetDescription())
    {
      if (!first) sb.append("," + newLine);
      sb.append(indentStr);
      sb.append("description");
      sb.append(space);
      sb.append(":").append(space);
      if (this.getDescription() == null) {
        sb.append("null");
      } else {
        sb.append(TBaseHelper.toString(this.getDescription(), indent + 1, prettyPrint));
      }
      first = false;
    }
    if (isSetName())
    {
      if (!first) sb.append("," + newLine);
      sb.append(indentStr);
      sb.append("name");
      sb.append(space);
      sb.append(":").append(space);
      if (this.getName() == null) {
        sb.append("null");
      } else {
        sb.append(TBaseHelper.toString(this.getName(), indent + 1, prettyPrint));
      }
      first = false;
    }
    if (isSetHasAC())
    {
      if (!first) sb.append("," + newLine);
      sb.append(indentStr);
      sb.append("hasAC");
      sb.append(space);
      sb.append(":").append(space);
      sb.append(TBaseHelper.toString(this.isHasAC(), indent + 1, prettyPrint));
      first = false;
    }
    sb.append(newLine + TBaseHelper.reduceIndent(indentStr));
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws TException {
    // check for required fields
  }

}

